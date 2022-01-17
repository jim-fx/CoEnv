<script lang="ts">
	export let animated = false;
	export let visible = true;
	export let visibleDelay = 0;
</script>

<svg
	class:animated
	class:visible
	xmlns="http://www.w3.org/2000/svg"
	viewBox="0 0 173.20508075688772 200"
	preserveAspectRatio="xMidYMid meet"
>
	<path
		style="--jan-delay: {visibleDelay}ms"
		vector-effect="non-scaling-stroke"
		d="M86.60254037844386 0L173.20508075688772 50L173.20508075688772 150L86.60254037844386 200L0 150L0 50Z"
	/>
</svg>

<style>
	svg {
		height: 100%;
		width: 100%;
	}

	path {
		stroke: var(--stroke, 'none');
		fill: var(--fill, white);
		stroke-width: var(--stroke-width, 2px);
	}

	svg.animated path {
		transition: opacity 0.3s ease;
		stroke-dasharray: 4000;
		stroke-dashoffset: 4000;
		animation: dash 4s ease-out forwards;
		animation-delay: var(--jan-delay);
	}

	@keyframes dash {
		to {
			stroke-dashoffset: 0;
		}
	}
</style>

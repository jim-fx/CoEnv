<script lang="ts">
	import { slideIndex, slideTitle } from '$lib/stores';
</script>

{#if $slideTitle.length}
	<p absolute bottom-4 left-4 m-0>{$slideTitle.replace('%I', $slideIndex + 1 + ' |')}</p>
{/if}
